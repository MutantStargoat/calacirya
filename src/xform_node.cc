#include <algorithm>
#include "xform_node.h"
#include "anim/anim.h"
#include "anim/track.h"


XFormNode::XFormNode()
{
	anm = new anm_node;
	anm_init_node(anm);
}

XFormNode::~XFormNode()
{
	anm_destroy_node(anm);
	delete anm;
}

void XFormNode::set_name(const char *name)
{
	anm_set_node_name(anm, name);
}

const char *XFormNode::get_name() const
{
	return anm_get_node_name(anm);
}

void XFormNode::set_interpolator(Interp in)
{
	anm_interpolator ain;

	switch(in) {
	case Interp::step:
		ain = ANM_INTERP_STEP;
		break;

	case Interp::linear:
		ain = ANM_INTERP_LINEAR;
		break;

	case Interp::cubic:
		ain = ANM_INTERP_CUBIC;
		break;
	}
	anm_set_interpolator(anm, ain);
	interp = in;
}

Interp XFormNode::get_interpolator() const
{
	return interp;
}

void XFormNode::set_extrapolator(Extrap ex)
{
	anm_extrapolator aex;

	switch(ex) {
	case Extrap::extend:
		aex = ANM_EXTRAP_EXTEND;
		break;

	case Extrap::clamp:
		aex = ANM_EXTRAP_CLAMP;
		break;

	case Extrap::repeat:
		aex = ANM_EXTRAP_REPEAT;
		break;
	}
	anm_set_extrapolator(anm, aex);
	extrap = ex;
}

Extrap XFormNode::get_extrapolator() const
{
	return extrap;
}

void XFormNode::add_child(XFormNode *child)
{
	children.push_back(child);
	anm_link_node(anm, child->anm);
}

void XFormNode::remove_child(XFormNode *child)
{
	auto it = std::find(children.begin(), children.end(), child);
	if(it != children.end()) {
		children.erase(it);
		anm_unlink_node(anm, child->anm);
	}
}

void XFormNode::set_position(const Vector3 &pos, long tmsec)
{
	anm_set_position(anm, v3_cons(pos.x, pos.y, pos.z), ANM_MSEC2TM(tmsec));
}

Vector3 XFormNode::get_node_position(long tmsec) const
{
	vec3_t p = anm_get_node_position(anm, ANM_MSEC2TM(tmsec));
	return Vector3(p.x, p.y, p.z);
}

void XFormNode::set_rotation(const Quaternion &quat, long tmsec)
{
	anm_set_rotation(anm, quat_cons(quat.s, quat.v.x, quat.v.y, quat.v.z), ANM_MSEC2TM(tmsec));
}

Quaternion XFormNode::get_node_rotation(long tmsec) const
{
	quat_t q = anm_get_node_rotation(anm, ANM_MSEC2TM(tmsec));
	return Quaternion(q.w, q.x, q.y, q.z);
}

void XFormNode::set_scaling(const Vector3 &pos, long tmsec)
{
	anm_set_scaling(anm, v3_cons(pos.x, pos.y, pos.z), ANM_MSEC2TM(tmsec));
}

Vector3 XFormNode::get_node_scaling(long tmsec) const
{
	vec3_t s = anm_get_node_scaling(anm, ANM_MSEC2TM(tmsec));
	return Vector3(s.x, s.y, s.z);
}

// these take hierarchy into account
Vector3 XFormNode::get_position(long tmsec) const
{
	vec3_t v = anm_get_position(anm, ANM_MSEC2TM(tmsec));
	return Vector3(v.x, v.y, v.z);
}

Quaternion XFormNode::get_rotation(long tmsec) const
{
	quat_t q = anm_get_rotation(anm, tmsec);
	return Quaternion(q.w, q.x, q.y, q.z);
}

Vector3 XFormNode::get_scaling(long tmsec) const
{
	vec3_t v = anm_get_scaling(anm, ANM_MSEC2TM(tmsec));
	return Vector3(v.x, v.y, v.z);
}

void XFormNode::set_pivot(const Vector3 &pivot)
{
	anm_set_pivot(anm, v3_cons(pivot.x, pivot.y, pivot.z));
}

Vector3 XFormNode::get_pivot() const
{
	vec3_t p = anm_get_pivot(anm);
	return Vector3(p.x, p.y, p.z);
}

void XFormNode::get_xform(long tmsec, Matrix4x4 *mat, Matrix4x4 *inv_mat) const
{
	if(mat) {
		anm_get_matrix(anm, (scalar_t(*)[4])mat, ANM_MSEC2TM(tmsec));
	}
	if(inv_mat) {
		anm_get_inv_matrix(anm, (scalar_t(*)[4])inv_mat, ANM_MSEC2TM(tmsec));
	}
}
