import React from 'react';
import { Joystick } from 'react-joystick-component';

const CarController = () => {

    const handleMove = (data) => {
        console.log('handleMove=', data)
    }

    const handleStop = (data) => {
        console.log('handleStop=', data)
    }

    return (
        <div className="car">
            <h1>Car Controller</h1>
            <Joystick size={100} baseColor="red" stickColor="blue" move={handleMove} stop={handleStop}></Joystick>
        </div>

    )
}

export {CarController}