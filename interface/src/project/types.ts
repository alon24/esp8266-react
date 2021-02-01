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
  btnMomemntary?: boolean;
  x?: number;
  y?: number;
  power?: number;
  action?: String;
}

export interface CarState1 {
  carOn: boolean;
  lightsOn?: boolean;
  ultraSoundOn: boolean;
  x?: number;
  y?: number;
  power?: number;
  useSteeringMotor?: boolean;
  btnMomemntary?: boolean;
  btnIntCount?: number;
  joystickData?: any;
}
