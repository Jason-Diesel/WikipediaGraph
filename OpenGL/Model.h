#pragma once
#include "Mesh.h"
#include <vector>
#include "ErrorHelper.h"
#include "Transform.h"
#include "Buffer.h"
#include "Animation.h"

struct materialConstBuffer{
    glm::vec4 Ka;//add ni here
    glm::vec4 Kd;//add d here
    glm::vec4 Ks;//ns here as w
    glm::vec4 Ke;//add materials flags here
	void operator=(const Material& m){
		this->Ka = glm::vec4(m.Ka, m.Ni);
		this->Kd = glm::vec4(m.Kd, m.d);
		this->Ks = glm::vec4(m.Ks, m.Ns);
		this->Ke = glm::vec4(m.Ke, m.materialFlags);
	};
};

enum class TypeOfModel {
	Default,
	Animated
};

class Model{
public:
	Model();
	virtual ~Model();
	std::vector<Mesh> &getMeshes();
	virtual void DirectRender(GLuint Topology = GL_TRIANGLES);
	void DirectRenderShadow();
	void setTransform(Transform transform);
	TypeOfModel GetModelType() const;
protected:
	TypeOfModel typeOfModel;
	uint32_t TransformBuffer;
	std::vector<Mesh> meshes;
};



