use main_window::window_loop;

mod main_window;

pub fn start_game() {
    window_loop();
}
// pub mod game_functions {

//     mod main_window {

//         fn start_window() {}

//         fn close_window() {}

//         fn pause_window() {}

//         mod renderer {

//             fn start_renderer() {}

//             fn pause_renderer() {}

//             fn stop_renderer() {}

//             mod world_gen {

//                 fn create_grid() {}

//                 fn create_world() {}

//                 fn save_world() {}

//                 mod player {

//                     fn spawn_player() {}

//                     fn kill_player() {}
//                 }
//             }
//         }
//     }
// }
