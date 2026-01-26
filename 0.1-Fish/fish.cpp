#include <stylizer/core/util/reaction.hpp>

import std.compat;
import stdmath.slang;
import stylizer;
import stylizer.spans;
import stylizer.load_file;
import stylizer.sdl3.window;
import stylizer.image;
import stylizer.model;
import stylizer.debug;

#include <math/namespace_alias.hpp>
using namespace stdmath::literals;

int main() {
	auto ctx = stylizer::context::create_default_with_error_handler();
	auto window = stylizer::sdl3::window::create(ctx, "Fish!", {800, 600});
	window.register_event_listener(ctx);

	auto fb = stylizer::color_depth_frame_buffer::create(
		ctx, window.texture_size()(), std::math::color32::from_hex("#FFF9E5"), window.texture_format()
	);

	auto material = stylizer::flat_material::create(ctx, fb,
		stylizer::image::load(ctx, "../../0.1-Fish/assets/fish.png")
			->upload(ctx)
			.configure_sampler(ctx)
			.move()
	);

	auto model = stylizer::model::load(ctx, "../../0.1-Fish/assets/fish.obj")
		->override_materials(material)
		.move();

	stylizer::utility_buffer util;
	util.camera.projection = std::math::perspective_matrix<float>(45._degrees, fb.size().xy().to_vector());
	util.camera.inverse_projection = inverse(util.camera.projection);
	util.camera.view = std::math::look_at_matrix<float>({0, 0, 2}, {0, 0, 0});
	util.camera.inverse_view = inverse(util.camera.view);

	stylizer::instance_data::buffer<1> instances;
	auto aabb = model.calculate_AABB();
	std::println("{}", aabb);

	stylizer::run_main_loop([&] -> bool {
		if(window.close_requested()) return false;

		ctx.per_frame(window, util);

		instances[0].model = homogenous_rotation_matrix(std::math::quaternion::from_euler_angles({0, util.time.total * 90, 0}));
		instances.upload(ctx);

		fb.draw_to(ctx, [&](stylizer::frame_buffer::render::pass& pass) {
			model.draw_instanced(ctx, pass, instances, util);
			stylizer::debug::draw_lines_instanced(ctx, pass, fb, aabb, instances, {1, 0, 0, 1}, util);
		});

		window.present(ctx, fb.color_texture());
		return true;
	});
}