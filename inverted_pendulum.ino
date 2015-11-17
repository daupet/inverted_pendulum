// 加速度センサからの入力ピン
const int pin_ax = 3;
const int pin_ay = 4;
const int pin_az = 5;

// モータへの出力ピン（左右で共通）
const int pin_mot_in1 = 8;
const int pin_mot_in2 = 9;
const int pin_motor = 10;

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
 * output: モータへの電圧出力 [mV]，ただし -5000～5000 の範囲
 */
void motor_output(int output);


void setup()
{
  pinMode(pin_motor,   OUTPUT);
  pinMode(pin_mot_in1, OUTPUT);
  pinMode(pin_mot_in1, OUTPUT);

//  Serial.begin(9600);
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


int get_angle(void)
{
  // 今回使う加速度センサは電源電圧3.3Vの場合，
  // 加速度0で1.65Vを出力するようになっている。
  // Arduinoでは0～5Vを0～1023で取得するので，
  // 1.65V÷5V×1023＝337.59 となる
  static const float offset = 337.59;

  // センサから加速度を取得する。
  float ax = analogRead(pin_ax) - offset;
  float ay = analogRead(pin_ay) - offset;
  float az = analogRead(pin_az) - offset;

  // x軸とz軸の加速度から偏角を求める。
  // 計算にはarctanの近似式を用いた：[http://blogs.yahoo.co.jp/fermiumbay2/38729661.html]より
  float tmp = -az/ax;
  float ang = (12*tmp*tmp+45)/(27*tmp*tmp+45)*tmp;

  // 1000倍してから整数として返す
  return (int)(ang*1000); // [10^-3 rad]
}


void motor_output(int output)
{
  // 出力値の絶対値をとる
  int _out = constrain(abs(output), 0, 5000);

  // 0～5000 の範囲で指定された電圧を 0～255 の範囲に縮小する。
  // 5000 * 0.051 = 255
  analogWrite(pin_motor, (int)((float)_out*0.051));

  // 出力値の符号に応じてモータドライバの回転方向を決める
  if (output >= 0)
  {
    digitalWrite(pin_mot_in1, HIGH);
    digitalWrite(pin_mot_in2, LOW);
  }
  else
  {
    digitalWrite(pin_mot_in1, LOW);
    digitalWrite(pin_mot_in2, HIGH);
  }
}

