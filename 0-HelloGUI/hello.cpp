#include <stylizer/core/util/reaction.hpp>
#include <imgui.h>

import std;
import stdmath.slang;
import stylizer;
import stylizer.imgui;
import stylizer.sdl3.window;

int main() {
	auto ctx = stylizer::context::create_default_with_error_handler();
	auto window = stylizer::sdl3::window::create(ctx, "Hello GUI", {800, 600});
	window.register_event_listener(ctx);

	auto fb = stylizer::single_texture_frame_buffer::create(
		ctx, window.texture_size()(), stdmath::color32::from_hex("#CCC"), window.texture_format()
	);
	stylizer::imgui gui(ctx, window);

	while(!window.close_requested()) {
		ctx.per_frame(window);

		fb.draw_to(ctx, [&](stylizer::graphics::render::pass& pass) {
			gui.new_frame([&] {
				gui.window("invisible", [&]{
					ImGui::TextColored(stylizer::convert(stdmath::color32::from_hex("#333")), "Hello GUI");
					ImGui::SetWindowPos(stylizer::convert(stdmath::float2{fb.size().xy().to_vector() / 2} - stylizer::convert(ImGui::GetWindowSize()) / 2));
				}, nullptr, ImGuiWindowFlags_Invisible);
			});

			gui.draw(pass);
		});

		window.present(ctx, fb.color_texture());
	}
}