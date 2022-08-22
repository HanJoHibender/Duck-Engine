use winit::event::{Event, VirtualKeyCode, ElementState, KeyboardInput, WindowEvent};
use winit::event_loop::{EventLoop, ControlFlow};

pub fn init(title:&str, width: i32, height: i32, event_loop: &EventLoop<()>) -> winit::window::Window{
    winit::window::WindowBuilder::new()
    .with_title(title)
    .with_inner_size(winit::dpi::LogicalSize::new(width, height))
    .build(event_loop)
    .expect("Failed to create window.")
}