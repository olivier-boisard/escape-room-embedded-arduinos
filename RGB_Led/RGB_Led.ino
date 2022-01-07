#define RED 6
#define GREEN 5
#define BLUE 3
#define TIMESTEP_MS 5

typedef struct {
  int red;
  int green;
  int blue;
} Color;

void writeColor(const Color& color) {
  analogWrite(RED, color.red);
  analogWrite(GREEN, color.green);
  analogWrite(BLUE, color.blue);
}

void fadeRedToGreen() {
  Color color;
  color.red = 255;
  color.green = 0;
  color.blue = 0;

  for(int i = 0; i < 255; i += 1) {
    color.red -= 1;
    color.green += 1;
    writeColor(color);
    delay(TIMESTEP_MS);
  }
}

void fadeGreenToBlue() {
  Color color;
  color.red = 0;
  color.green = 255;
  color.blue = 0;
  
  for(int i = 0; i < 255; i += 1) {
    color.green -= 1;
    color.blue += 1;
    writeColor(color);
    delay(TIMESTEP_MS);
  }
}

void fadeBlueToRed() {
  Color color;
  color.red = 0;
  color.green = 0;
  color.blue = 255;
  
  for(int i = 0; i < 255; i += 1) {
    color.blue -= 1;
    color.red += 1;
    writeColor(color);
    delay(TIMESTEP_MS);
  }
}
