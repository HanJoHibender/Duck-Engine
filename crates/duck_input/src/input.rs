use winit::{
    event::{self, ElementState, Event, KeyboardInput, VirtualKeyCode, WindowEvent},
    window::Window,
};

pub enum UserEvent {
    Event,
}

pub fn event_handler(event: Event<UserEvent>, window: Window) {
    match event {
        Event::NewEvents(event) => todo!(),
        Event::DeviceEvent { event, .. } => todo!(),
        Event::UserEvent(event) => todo!(),
        Event::Suspended => todo!(),
        Event::Resumed => todo!(),
        Event::MainEventsCleared => todo!(),
        Event::RedrawRequested(_) => todo!(),
        Event::RedrawEventsCleared => todo!(),
        Event::LoopDestroyed => todo!(),
        Event::WindowEvent { window_id, event } => todo!(),
    }
}
