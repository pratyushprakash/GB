#include "framebuffer.hpp"

FrameBuffer::FrameBuffer(uint height_arg, uint width_arg):
  height(height_arg),
  width(width_arg),
  buffer(height*width, Color::White){}

inline uint FrameBuffer::get_pixel_index(uint x, uint y){
  return y*width + x;
}

void FrameBuffer::reset(){
  for(uint i=0; i<buffer.size(); i++)
    buffer[i] = Color::White;
}

Color FrameBuffer::get_pixel(uint x, uint y){
  return buffer[get_pixel_index(x, y)];
}

void FrameBuffer::set_pixel(uint x, uint y, Color color){
  buffer[get_pixel_index(x, y)] = color;
}
