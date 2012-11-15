#include <stdio.h>
#include <stdlib.h>

#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "calacirya.h"

static bool init();
static void cleanup();
static void disp();
static void reshape(int x, int y);
static void keydown(unsigned char key, int x, int y);

static RenderContext ctx;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGB);
	glutCreateWindow("Calacirya render");

	glutDisplayFunc(disp);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keydown);

	if(!init()) {
		return 1;
	}

	glutMainLoop();
	return 0;
}

static bool init()
{
	calacirya_init();

	ctx.scn = new Scene;
	ctx.scn->set_background(Vector3(0.2, 0.3, 0.4));

	ctx.opt.width = 640;
	ctx.opt.height = 300;

	ctx.framebuf = new Pixmap;
	ctx.framebuf->width = ctx.opt.width;
	ctx.framebuf->height = ctx.opt.height;
	ctx.framebuf->pixels = new float[ctx.framebuf->width * ctx.framebuf->height * 3];
	memset(ctx.framebuf->pixels, 0, ctx.framebuf->width * ctx.framebuf->height * 3 * sizeof *ctx.framebuf->pixels);

	Material *mtl = new Material;
	mtl->add_brdf(get_brdf("lambert"));
	mtl->add_brdf(get_brdf("phong"));
	mtl->set_attrib("diffuse", Vector3(0.3, 0.4, 0.9));
	mtl->set_attrib("specular", Vector3(0.8, 0.8, 0.8));
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, ctx.opt.width, ctx.opt.height, 0, GL_RGB, GL_FLOAT, ctx.framebuf->pixels);

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

	float *fbptr = ctx.framebuf->pixels;

	for(int i=0; i<ctx.opt.height; i++) {
		if(!done_rend) {
			render_scanline(&ctx, i);
		}

		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, i, ctx.opt.width, 1, GL_RGB, GL_FLOAT, fbptr);
		fbptr += ctx.opt.width * 3;

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
}

static void reshape(int x, int y)
{
	glViewport(0, 0, x, y);
}

static void keydown(unsigned char key, int x, int y)
{
	if(key == 27) {
		exit(0);
	}
}
