import ListGroup from "react-bootstrap/ListGroup";
import { Container, Button } from "react-bootstrap";
import MyContainers from "./components/MyContainers";

export default function Home() {
    return (
        <Container fluid>
            <div style={{ width: "80%", margin: "0 auto", paddingTop: "2%" }}>
                <h1>Home</h1>
                <ListGroup>
                    <MyContainers></MyContainers>
                    <ListGroup.Item>
                        <Button href="/add_container" variant="outline-primary">
                            + Add
                        </Button>
                    </ListGroup.Item>
                </ListGroup>
            </div>
        </Container>
    );
}
