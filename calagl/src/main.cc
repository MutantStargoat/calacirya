#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <algorithm>

#include <GL/glew.h>

#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#ifndef GL_RGB16F
#define GL_RGB16F	0x881B
#endif

#include "calacirya.h"
#include "sdr.h"

static bool init();
static void cleanup();
static void disp();
static void reshape(int x, int y);
static void keydown(unsigned char key, int x, int y);
static void keyup(unsigned char key, int x, int y);
static void passive(int x, int y);
static bool have_glext(const char *name);

static RenderContext ctx;

static Shader *postsdr;
static SdrProg *postprog;

static const char *postsdr_source =
	"uniform sampler2D tex;\n"
	"uniform float inv_gamma;\n"
	"void main()\n"
	"{\n"
	"    vec3 col = texture2D(tex, gl_TexCoord[0].st).xyz;\n"
	"    gl_FragColor = vec4(pow(col, vec3(inv_gamma)), 1.0);\n"
	"}\n";

static float gamma_value = 2.2;


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutCreateWindow("Calacirya render");

	glutDisplayFunc(disp);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keydown);
	glutKeyboardUpFunc(keyup);

	glewInit();

	if(!init()) {
		return 1;
	}

	glutMainLoop();
	return 0;
}

static bool init()
{
	calacirya_init();

	ctx.load_config("calacirya.conf");

	ctx.scn = new Scene;
	ctx.scn->set_background(Vector3(0.04, 0.06, 0.1));

	ctx.framebuf = new Pixmap;
	ctx.framebuf->create(ctx.opt.width, ctx.opt.height);

	ctx.set_block_size(ctx.opt.blksize, ctx.opt.blksize);

	Material *mtl = new Material;
	mtl->add_brdf(get_brdf("lambert"));
	mtl->add_brdf(get_brdf("phong"));
	mtl->set_attrib("diffuse", Vector3(0.7, 0.3, 0.2));
	mtl->set_attrib("specular", Vector3(0.6, 0.6, 0.6));
	mtl->set_attrib("shininess", 80.0);

	Sphere *sph = new Sphere;
	sph->set_radius(1.0);
	sph->set_position(Vector3(0, 0, 0));
	sph->set_material(mtl);
	ctx.scn->add_surface(sph);

	Camera *cam = new Camera;
	cam->set_position(Vector3(0, 0, -6));
	ctx.scn->add_camera(cam);

	Light *lt = new Light;
	lt->set_position(Vector3(-5, 5, -5));
	ctx.scn->add_light(lt);

	glutReshapeWindow(ctx.opt.width, ctx.opt.height);

	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	unsigned int texfmt = have_glext("GL_ARB_texture_float") ? GL_RGB16F : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, texfmt, ctx.opt.width, ctx.opt.height, 0, GL_RGB, GL_FLOAT, ctx.framebuf->pixels);

	// load the gamma correction shader
	postsdr = new Shader(GL_FRAGMENT_SHADER);
	postsdr->set_source(postsdr_source);

	postprog = new SdrProg;
	postprog->add_shader(postsdr);

	if(!postprog->link()) {
		return false;
	}
	bind_program(postprog);

	assert(glGetError() == GL_NO_ERROR);

	atexit(cleanup);
	return true;
}

static void cleanup()
{
	calacirya_destroy();
}

static void disp()
{
	static bool done_rend;

	postprog->set_uniform("inv_gamma", 1.0f / gamma_value);

	if(!done_rend) {
		float *fbptr = ctx.framebuf->pixels;

		std::sort(ctx.blocks, ctx.blocks + ctx.num_blocks,
			[](const FrameBlock &a, const FrameBlock &b) { return a.prio < b.prio; });

		for(int i=0; i<ctx.num_blocks; i++) {
			fbptr = ctx.framebuf->pixels +
				(ctx.blocks[i].y * ctx.framebuf->width + ctx.blocks[i].x) * 3;

			render_block(&ctx, ctx.blocks[i]);

			for(int j=0; j<ctx.blocks[i].height; j++) {
				glTexSubImage2D(GL_TEXTURE_2D, 0, ctx.blocks[i].x, ctx.blocks[i].y + j,
						ctx.blocks[i].width, 1, GL_RGB, GL_FLOAT, fbptr);
				fbptr += ctx.framebuf->width * 3;
			}

			glBegin(GL_QUADS);
			glTexCoord2f(0, 1);
			glVertex2f(-1, -1);
			glTexCoord2f(1, 1);
			glVertex2f(1, -1);
			glTexCoord2f(1, 0);
			glVertex2f(1, 1);
			glTexCoord2f(0, 0);
			glVertex2f(-1, 1);
			glEnd();

			glFlush();
		}

		done_rend = true;
	} else {
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex2f(-1, -1);
		glTexCoord2f(1, 1);
		glVertex2f(1, -1);
		glTexCoord2f(1, 0);
		glVertex2f(1, 1);
		glTexCoord2f(0, 0);
		glVertex2f(-1, 1);
		glEnd();

		glFlush();
	}

	assert(glGetError() == GL_NO_ERROR);
}

static void reshape(int x, int y)
{
	glViewport(0, 0, x, y);
}

static bool keystate[128];
static int prev_x, prev_y;

static void keydown(unsigned char key, int x, int y)
{
	if(key == 27) {
		exit(0);
	}

	if(key < sizeof keystate / sizeof *keystate) {
		keystate[key] = true;
	}
	glutPassiveMotionFunc(passive);
	prev_x = x;
	prev_y = y;
}

static void keyup(unsigned char key, int x, int y)
{
	if(key < sizeof keystate / sizeof *keystate) {
		keystate[key] = false;
	}
	glutPassiveMotionFunc(0);
}

static void passive(int x, int y)
{
	int dx = x - prev_x;
	//int dy = y - prev_y;

	prev_x = x;

	if(keystate['g'] || keystate['G']) {
		gamma_value += 4.0 * (float)dx / (float)ctx.opt.width;
		if(gamma_value < 0.01) {
			gamma_value = 0.01;
		}
		printf("gamma: %f\n", gamma_value);
		glutPostRedisplay();
	}
}

static bool have_glext(const char *name)
{
	const char *ptr = strstr((const char*)glGetString(GL_EXTENSIONS), name);
	if(ptr && !isalnum(ptr[strlen(name)])) {
		return true;
	}
	return false;
}
