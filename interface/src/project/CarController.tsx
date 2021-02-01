import React, {Component} from 'react';
import { Joystick } from 'react-joystick-component';
import {WEB_SOCKET_ROOT} from "../api";
import {
    BlockFormControlLabel,
    SectionContent,
    webSocketController,
    WebSocketControllerProps,
    WebSocketFormLoader,
    WebSocketFormProps
} from "../components";
import {CarState} from "./types";
import {ValidatorForm} from "react-material-ui-form-validator";
import {Box, Switch, Typography} from "@material-ui/core";

export const CAR_SETTINGS_WEBSOCKET_URL = WEB_SOCKET_ROOT + "carState";

type CarStateWebSocketControllerProps = WebSocketControllerProps<CarState>;

class CarStateWebSocketController extends Component<CarStateWebSocketControllerProps> {

    render() {
        return (
            <SectionContent title='WebSocket Controller' titleGutter>
                <WebSocketFormLoader
                    {...this.props}
                    render={props => (
                        <CarStateWebSocketControllerForm {...props} />
                    )}
                />
            </SectionContent>
        )
    }
}

const CarController = webSocketController(CAR_SETTINGS_WEBSOCKET_URL, 100, CarStateWebSocketController);

type CarStateWebSocketControllerFormProps = WebSocketFormProps<CarState>;

function CarStateWebSocketControllerForm(props: CarStateWebSocketControllerFormProps) {
    const { data, saveData, setData } = props;

    // const changeLedOn = (event: React.ChangeEvent<HTMLInputElement>) => {
    //     setData({ led_on: event.target.checked }, saveData);
    // }

    const changeValue = (event: React.ChangeEvent<HTMLInputElement>) => {

    }

    const handleMove = (data) => {
        console.log('handleMove=', data);
        // // setData({ led_on: event.target.checked }, saveData);
        setData({ btnMomemntary: true }, saveData);
    }

    const handleStop = (data) => {
        console.log('handleStop=', data)
    }

    return (
        <ValidatorForm onSubmit={saveData}>
            <Box bgcolor="primary.main" color="primary.contrastText" p={2} mt={2} mb={2}>
                <Typography variant="body1">
                    The switch below controls the LED via the WebSocket. It will automatically update whenever the LED state changes.
                </Typography>
            </Box>
            <BlockFormControlLabel
                control={
                    <Switch
                        checked={data.btnMomemntary}
                        color="primary"
                    />
                }
                label="Button State?"
            />
            <div className="car">
                <h1>Car Controller</h1>
                <Joystick size={100} baseColor="red" stickColor="blue" move={handleMove} stop={handleStop}></Joystick>
            </div>

            <pre>
                {JSON.stringify(data, null, 2)}
            </pre>

        </ValidatorForm>
    );
}

export {CarController}
