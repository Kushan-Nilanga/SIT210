import Button from "react-bootstrap/Button";
import ListGroup from "react-bootstrap/ListGroup";
import axios from "axios";
import { useEffect, useState } from "react";

export default function () {
    const [items, setItems] = useState([]);

    useEffect(() => {
        axios.get("/api/container/get").then((res) => {
            setItems(res.data);
        });
    }, []);

    return Object.keys(items).map((d) => (
        <ListGroup.Item key={d}>
            <div>
                <Button href={"/container/?uuid=" + d} variant="light">
                    {items[d].name}
                </Button>
                <Button
                    variant="outline-danger"
                    size="sm"
                    id={d}
                    style={{ float: "right", marginTop: "0.2em" }}
                    onClick={(event) => {
                        axios.post("/api/container/remove", {
                            payload: { id: event.target.id },
                        });
                    }}
                    href="/"
                >
                    Delete
                </Button>
            </div>
        </ListGroup.Item>
    ));
}
