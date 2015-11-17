int pin_ax = 3;
int pin_ay = 4;
int pin_az = 5;
int ax_s = 0;
int ay_s = 0;
int az_s = 0;

double ax = 0.0;
double ay = 0.0;
double az = 0.0;

void get_accel(double* ax, double* ay, double* az);

void setup() {
  Serial.begin(9600);
  Serial.println("x    y    z");
}

void loop() {
  get_accel(&ax, &ay, &az);



//  set_motor_torque(m1, m2);
  
  Serial.print(ax);
  Serial.print("  ");
  Serial.print(ay);
  Serial.print("  ");
  Serial.print(az);
  Serial.print("\n");
}

void get_accel(double* ax, double* ay, double* az)
{
  ax_s = analogRead(pin_ax);
  ay_s = analogRead(pin_ay);
  az_s = analogRead(pin_az);

  *ax = ax_s - 337.59;
  *ay = ay_s - 337.59;
  *az = az_s - 337.59;
}

