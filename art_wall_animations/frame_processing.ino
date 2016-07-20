int current_frame = 0;
int animation_frame_counts[1] = {10};
int current_animation = 0;

void initialize_animations() {
  
}

void next_frame() {
  if (current_animation != 0) {
    current_frame = (current_frame >= animation_frame_counts[current_animation]) ? 0 : current_frame++;
  }
}

