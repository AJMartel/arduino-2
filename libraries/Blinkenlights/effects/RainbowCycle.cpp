// This file is included from Effect.cpp

#include "Pixel.h"

RainbowCycle::RainbowCycle(Selection *selection, uint32_t wait) : Effect(selection) {
  this->current_color = 0;
  this->wait = wait;
}

void RainbowCycle::next_step() {
  // Check if enough time has passed
  unsigned long current_time = millis();
  if (current_time - this->last_execution < this->wait) {
    return;
  }

  // Do our thing
  int i, num_pixels;
  num_pixels = this->selection->width() * this->selection->height();
  for (i = 0; i < num_pixels; i++) {
    // tricky math! we use each pixel as a fraction of the full 256-color wheel (thats the i / num_pixels part)
    // Then add in current_color which makes the colors go around per pixel
    // the % 256 is to make the wheel cycle around
    this->selection->get(i)->set_pixel_color(Effect::wheel( ((i * 256 / num_pixels) + this->current_color) % 256 ));
  }  

  // Update state
  this->current_color++;
  this->current_color = this->current_color % 256;
  this->last_execution = current_time;
}

void RainbowCycle::print() {
  Serial.println("----------------RainbowCycle effect:-----------------------------");
  Serial.print("current_color = ");
  Serial.print(current_color, DEC);
  Serial.print(", wait = ");
  Serial.print(wait, DEC);
  Serial.print(", last_execution = ");
  Serial.println(last_execution, DEC);
  this->selection->print();
}
