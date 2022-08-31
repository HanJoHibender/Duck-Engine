pub mod window_types {
    #![allow(clippy::single_match)]

    #[cfg(not(target_arch = "wasm32"))]
    use simple_logger::SimpleLogger;
    use winit::{
        event::Event,
        // event::{Event, WindowEvent},
        event_loop::{EventLoop, EventLoopBuilder},
        window::{Window, WindowBuilder},
    };

    #[derive(Debug, Clone, Copy)]
    pub enum UserEvent {
        Event,
    }

    #[allow(dead_code)]
    pub fn get_event_loop() -> EventLoop<UserEvent> {
        let mut event_loop = EventLoopBuilder::with_user_event().build();
        return event_loop;
    }

    pub fn get_window(title: &str, event_loop: EventLoop<UserEvent>) -> Window {
        SimpleLogger::new().init().unwrap();

        let window = WindowBuilder::new()
            .with_title(title)
            .build(&event_loop)
            .unwrap();
        return window;
    }
    pub fn simple_proxy_listener(event: UserEvent, event_loop: EventLoop<UserEvent>) {
        // `EventLoopProxy` allows you to dispatch custom events to the main Winit event
        // loop from any thread.
        let event_loop_proxy = event_loop.create_proxy();
        std::thread::spawn(move || {
            // Wake up the `event_loop` once every second and dispatch a custom event
            // from a different thread.
            loop {
                std::thread::sleep(std::time::Duration::from_secs(1));
                event_loop_proxy.send_event(event).ok();
            }
        });
    }

    #[cfg(target_arch = "wasm32")]
    fn simple_window() {
        panic!("This example is not supported on web.");
    }
}
