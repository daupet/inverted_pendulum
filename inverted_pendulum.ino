// 加速度センサからの入力ピン
const int pin_ax = 3;
const int pin_ay = 4;
const int pin_az = 5;

// 左右モータへの出力ピン
const int pin_lmot = 8;
const int pin_rmot = 9;

/**
 * 現在の車体の傾きを取得する。
 * 角度の表現は，加速度センサのx軸を0radとして，
 * y軸回りの方向を正方向とする。
 *
 * return: 現在の車体の傾き角度 [10^-3 rad]
 */
int get_angle(void);

/**
 * モータへの出力を設定する。
 *
 *
 * output: モータへの電圧出力 [mV]
 */
void motor_output(int output);


void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int angle;   // 車体の傾き [10^-3 rad]
  int dev;       // 目標値と現在の傾きとの偏差 [10^-3 rad]
  int output;  // モータに入力する電圧 [mV]

  int Kp = 1.0;         // 比例ゲイン
  int angle_cmd = 580;  // 車体傾きの目標値 [10^-3 rad]

  // 車体の傾きを取得する
  angle = get_angle();

  // 車体の傾きの偏差（目標値と現在値の差）を求め，それをゲイン倍してモータ出力を計算する

  Serial.print(angle);
  Serial.print("\n");

  output = 100;
  // モータにトルクを入力する
  motor_output(output);
}


int get_angle_bak(void)
{
  // 今回使う加速度センサは電源電圧3.3Vの場合，
  // 加速度0で1.65Vを出力するようになっている。
  // Arduinoでは0～5Vを0～1023で取得するので，
  // 1.65V÷5V×1023＝337.59 ―×10→ 3375 となる
  static const int offset = 3375;

  // センサから加速度を取得する。
  int ax = analogRead(pin_ax) * 10 - offset;
  int ay = analogRead(pin_ay) * 10 - offset;
  int az = analogRead(pin_az) * 10 - offset;

  // x軸とz軸の加速度から偏角を求める。
  // 計算にはarctanの近似式を用いた：[http://blogs.yahoo.co.jp/fermiumbay2/38729661.html]より
  int tmp = -(az*10)/ax;
/* */
  Serial.print(tmp);
  Serial.print("   ");
/* */
/* */
  Serial.print(ax);
  Serial.print("   ");
/* *
  Serial.print(ay);
  Serial.print("   ");
/* */
  Serial.print(az);
  Serial.print("   ");
/* */

  return (12*tmp*tmp+4500)/(27*tmp*tmp+4500)*tmp*100; // [10^-3 rad]
}


int get_angle(void)
{
  // 今回使う加速度センサは電源電圧3.3Vの場合，
  // 加速度0で1.65Vを出力するようになっている。
  // Arduinoでは0～5Vを0～1023で取得するので，
  // 1.65V÷5V×1023＝337.59 ―×10→ 3375 となる
  static const float offset = 337.59;

  // センサから加速度を取得する。
  float ax = analogRead(pin_ax) - offset;
  float ay = analogRead(pin_ay) - offset;
  float az = analogRead(pin_az) - offset;

  // x軸とz軸の加速度から偏角を求める。
  // 計算にはarctanの近似式を用いた：[http://blogs.yahoo.co.jp/fermiumbay2/38729661.html]より
  float tmp = -az/ax;
/* *
  Serial.print(tmp);
  Serial.print("   ");
/* */
/* *
  Serial.print(ax);
  Serial.print("   ");
/* *
  Serial.print(ay);
  Serial.print("   ");
/* *
  Serial.print(az);
  Serial.print("   ");
/* */
  float ang = (12*tmp*tmp+45)/(27*tmp*tmp+45)*tmp;
/* *
  Serial.print(ang);
  Serial.print("   ");
/* */

  return (int)(ang*1000); // [10^-3 rad]
}


void motor_output(int output)
{
  analogWrite(pin_lmot, output);
  analogWrite(pin_rmot, output);
}

