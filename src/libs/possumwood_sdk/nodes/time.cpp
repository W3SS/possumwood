#include <possumwood_sdk/node_implementation.h>
#include <possumwood_sdk/app.h>

#include <dependency_graph/values.inl>
#include <dependency_graph/attr.inl>
#include <dependency_graph/datablock.inl>
#include <dependency_graph/port.inl>
#include <dependency_graph/node.inl>

namespace {

dependency_graph::OutAttr<float> a_time;

void init(possumwood::Metadata& meta) {
	meta.addAttribute(a_time, "time");

	meta.setCompute([](dependency_graph::Values& vals) {
		vals.set(a_time, possumwood::App::instance().time());

		return dependency_graph::State();
	});
}

/// This is a hack - "time" nodes have a single output, set by a callback in the
/// possumwood SDK's App object
possumwood::NodeImplementation s_impl("time", init);

}
