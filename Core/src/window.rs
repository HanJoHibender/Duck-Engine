use std::sync::Arc;
use std::task::Context;
use vulkano::{
    buffer::{BufferUsage, CpuAccessibleBuffer, TypedBufferAccess},
    command_buffer::{
        AutoCommandBufferBuilder, CommandBufferUsage, RenderPassBeginInfo, SubpassContents,
    },
    device::{
        physical::{PhysicalDevice, PhysicalDeviceType},
        Device, DeviceCreateInfo, DeviceExtensions, QueueCreateInfo,
    },
    image::{view::ImageView, ImageAccess, ImageUsage, SwapchainImage},
    impl_vertex,
    instance::{Instance, InstanceCreateInfo},
    pipeline::{
        graphics::{
            input_assembly::InputAssemblyState,
            vertex_input::BuffersDefinition,
            viewport::{Viewport, ViewportState},
        },
        GraphicsPipeline,
    },
    render_pass::{Framebuffer, FramebufferCreateInfo, RenderPass, Subpass},
    swapchain::{
        acquire_next_image, AcquireError, Swapchain, SwapchainCreateInfo, SwapchainCreationError,
    },
    sync::{self, FlushError, GpuFuture},
};
use vulkano::pipeline::Pipeline;
use vulkano::swapchain::Surface;
use vulkano_win::VkSurfaceBuild;
use winit::{
    event::{Event, WindowEvent},
    event_loop::{ControlFlow, EventLoop},
    window::{Window, WindowBuilder},
};

struct window_info{
    title:str,
    dimensions:Vec<i32,i32>,
    event_loop:EventLoop<T>,
    surface:Arc<Surface<Window>>,
    viewport:Viewport,
    framebuffers:Vec<Framebuffer>,
    swapchain:Swapchain<T>,
    recreate_swapchain:bool,
    graphics_pipeline:GraphicsPipeline,
    render_pass:RenderPass,
}

pub struct duck_window{
    window_info:window_info,
}

impl duck_window{
    pub fn new( title: &str, width:i32, height:i32) -> Self{
        Self.window_info.title = **title;
        Self.window_info.dimensions = vec![width][height];
        Self
    }
    pub fn init(&mut self){
        let required_extensions = vulkano_win::required_extensions();

        let instance = Instance::new(InstanceCreateInfo {
            enabled_extensions: required_extensions,

            enumerate_portability: true,
            ..Default::default()
        })
            .unwrap();

        self.window_info.event_loop = EventLoop::new();
        self.window_info.surface = WindowBuilder::new()
            .build_vk_surface(&event_loop, instance.clone())
            .unwrap();

        let device_extensions = DeviceExtensions {
            khr_swapchain: true,
            ..DeviceExtensions::none()
        };
    }
    pub fn update(&self){

    }
}