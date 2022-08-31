// use duck_internal::bender_window::window::simple_window;
use duck_internal::bender_window::window::window_types::{
    get_event_loop, get_window, simple_proxy_listener, UserEvent,
};

// use duck_internal::bender_window::window::simple_window::event_loop_proxy;
// use duck_internal::duck_input::input::event_handler;
fn main() {
    // spawn window
    let event_loop = get_event_loop();
    // let window =
    get_window("Duck Engine!", event_loop);

    // event_handler(event, window);
    // simple_proxy_listener(Event<UserEvent>, event_loop);
    // innitialise render
    // window.insert_render();
    // generate World
    // visualise
}
