import axios from "axios";
import { useState } from "react";
import { Button, Card } from "react-bootstrap";

export default function () {
    const defConDepth = 14.0;
    const [payload, setPayload] = useState({ con_depth: 14.0 });

    function newContainerSubmit() {
        axios.post("/api/container/add", {
            payload: payload,
        });
    }

    function updateState(key, val) {
        var state = payload;
        state[key] = val;
        setPayload(state);
    }

    return (
        <div style={{ width: "80%", margin: "0 auto", paddingTop: "2%" }}>
            <h5>
                <a href="\"> &#60; Home </a>
            </h5>
            <h1>Add Container</h1>

            <div>
                <Card style={{ padding: "1em" }}>
                    <label>
                        Container Name: &nbsp;
                        <input
                            type="text"
                            onChange={(event) =>
                                updateState("name", event.target.value)
                            }
                        />
                    </label>
                    <br />
                    <label>
                        Bluetooth UUID: &nbsp;
                        <input
                            type="text"
                            onChange={(event) =>
                                updateState("id", event.target.value)
                            }
                        />
                    </label>
                </Card>
                <br />
                <Card style={{ padding: "1em" }}>
                    <label>
                        Temperature threshold (in &#176;C): &nbsp;
                        <input
                            type="number"
                            min="-100"
                            max="100"
                            step="0.1"
                            onChange={(event) =>
                                updateState(
                                    "temp_thresh",
                                    parseFloat(event.target.value)
                                )
                            }
                        />
                    </label>
                </Card>
                <br />
                <Card style={{ padding: "1em" }}>
                    <label>
                        Humidity threshold (in %): &nbsp;
                        <input
                            type="number"
                            min="0"
                            max="100"
                            step="0.1"
                            onChange={(event) =>
                                updateState(
                                    "hum_thresh",
                                    parseFloat(event.target.value)
                                )
                            }
                        />
                    </label>
                </Card>
                <br />
                <Card style={{ padding: "1em" }}>
                    <label>
                        Container depth (in cm): &nbsp;
                        <input
                            type="number"
                            min="10"
                            max="100"
                            step="0.1"
                            defaultValue={defConDepth}
                            onChange={(event) =>
                                updateState(
                                    "con_depth",
                                    parseFloat(event.target.value || "15.0")
                                )
                            }
                        />
                    </label>
                    <br />
                    <label>
                        Amount threshold (in %): &nbsp;
                        <input
                            type="number"
                            min="0"
                            max="100"
                            step="0.1"
                            onChange={(event) =>
                                updateState(
                                    "amt_thresh",
                                    parseFloat(event.target.value)
                                )
                            }
                        />
                    </label>
                </Card>
                <br />
                <Button
                    variant="outline-primary"
                    onClick={newContainerSubmit}
                    href="/"
                >
                    Submit
                </Button>
            </div>
        </div>
    );
}
