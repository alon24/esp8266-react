export interface LightState {
  led_on: boolean;
  lightsOn: boolean;
}

export interface LightMqttSettings { 
  unique_id : string;
  name: string;
  mqtt_path : string;
}

export interface CarState {
  btnMomemntary: boolean;
}

export interface CarState1 {
  carOn: boolean;
  lightsOn?: boolean;
  ultraSoundOn: boolean;
  leftMotorPWM?: number;
  rightMotorPWM?: number;
  leftMotorDir?: number;
  rightMotorDir?: number;
  pwmModulation?: number;
  useSteeringMotor?: boolean;
  btnMomemntary?: boolean;
  btnIntCount?: number;
  joystickData?: any;
}
