#include <possumwood_sdk/node_implementation.h>

#include <dependency_graph/values.inl>
#include <dependency_graph/attr.inl>
#include <dependency_graph/datablock.inl>
#include <dependency_graph/port.inl>
#include <dependency_graph/node.inl>

#include <OpenMesh/Tools/Decimater/DecimaterT.hh>

#include "datatypes/decimater_module.h"

#include "io/decimater_module.h"
#include "io/mesh.h"

#include "openmesh.h"

namespace {

dependency_graph::InAttr<std::vector<DecimaterModule>> a_modules;
dependency_graph::InAttr<std::shared_ptr<const Mesh>> a_inMesh;
dependency_graph::OutAttr<std::shared_ptr<const Mesh>> a_outMesh;

void compute(dependency_graph::Values& data) {
	std::vector<DecimaterModule> modules = data.get(a_modules);
	std::shared_ptr<const Mesh> inMesh = data.get(a_inMesh);

	if(inMesh) {
		std::unique_ptr<Mesh> mesh(new Mesh(*inMesh));

		OpenMesh::Decimater::DecimaterT<Mesh> decimater(*mesh);

		for(auto& mod : modules)
			mod(decimater);

		decimater.initialize();
		decimater.decimate();
		mesh->garbage_collection();

		data.set(a_outMesh, std::shared_ptr<const Mesh>(mesh.release()));
	}
	else
		data.set(a_outMesh, std::shared_ptr<const Mesh>());
}

void init(possumwood::Metadata& meta) {
	meta.addAttribute(a_modules, "modules");
	meta.addAttribute(a_inMesh, "input");
	meta.addAttribute(a_outMesh, "output");

	meta.addInfluence(a_modules, a_outMesh);
	meta.addInfluence(a_inMesh, a_outMesh);

	meta.setCompute(compute);
}

possumwood::NodeImplementation s_impl("openmesh/decimater/decimater", init);

}
