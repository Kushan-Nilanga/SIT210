import axios from "axios";
import { useState } from "react";
import { Button } from "react-bootstrap";

export default function () {
    const [cont_name, setName] = useState([]);
    const [cont_uuid, setUuid] = useState([]);

    function newContainerSubmit() {
        axios.post("/api/container/add", {
            payload: {
                id: cont_uuid,
                name: cont_name,
            },
        });
    }

    return (
        <div style={{ width: "80%", margin: "0 auto", paddingTop: "2%" }}>
            <h5>
                <a href="\"> &#60; Home </a>
            </h5>
            <h1>Add Container</h1>

            <div>
                <label>
                    Container Name: &nbsp;
                    <input
                        type="text"
                        onChange={(event) => {
                            setName(event.target.value);
                        }}
                    />
                </label>
                <br />
                <br />
                <label>
                    Bluetooth UUID: &nbsp;
                    <input
                        type="text"
                        onChange={(event) => {
                            setUuid(event.target.value);
                        }}
                    />
                </label>
                <br />
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
