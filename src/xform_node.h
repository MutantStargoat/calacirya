#ifndef XFORM_NODE_H_
#define XFORM_NODE_H_

#include <list>
#include "vmath/vector.h"
#include "vmath/quat.h"
#include "vmath/matrix.h"

enum class Interp { step, linear, cubic };
enum class Extrap { extend, clamp, repeat };

struct anm_node;

// XXX all time arguments are milliseconds

class XFormNode {
private:
	struct anm_node *anm;
	std::list<XFormNode*> children;

	Interp interp;
	Extrap extrap;

public:
	XFormNode();
	virtual ~XFormNode();

	void set_name(const char *name);
	const char *get_name() const;

	void set_interpolator(Interp in);
	Interp get_interpolator() const;
	void set_extrapolator(Extrap ex);
	Extrap get_extrapolator() const;

	void add_child(XFormNode *child);
	void remove_child(XFormNode *child);

	void set_position(const Vector3 &pos, long tmsec);
	Vector3 get_node_position(long tmsec) const;

	void set_rotation(const Quaternion &quat, long tmsec);
	Quaternion get_node_rotation(long tmsec) const;

	void set_scaling(const Vector3 &pos, long tmsec);
	Vector3 get_node_scaling(long tmsec) const;

	// these take hierarchy into account
	Vector3 get_position(long tmsec) const;
	Quaternion get_rotation(long tmsec) const;
	Vector3 get_scaling(long tmsec) const;

	void set_pivot(const Vector3 &pivot);
	Vector3 get_pivot() const;

	void get_xform(long tmsec, Matrix4x4 *mat, Matrix4x4 *inv_mat = 0) const;
};



#endif	// XFORM_NODE_H_
