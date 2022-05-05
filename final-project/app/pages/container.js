import axios from "axios";
import { useRouter } from "next/router";
import { useEffect, useState } from "react";

export default function () {
    const router = useRouter();
    const uuid = router.query.uuid;

    const [container, setContainer] = useState([]);

    useEffect(() => {
        axios.post("/api/container/get?uuid=" + uuid).then((res) => {
            setContainer(res.data);
        });
    }, [router.isReady]);

    return (
        <div style={{ width: "80%", margin: "0 auto", paddingTop: "2%" }}>
            <h5>
                <a href="\"> &#60; Home </a>
            </h5>
            <h1>{container.name}</h1>
            <h6>uuid: {uuid}</h6>
            {JSON.stringify(container.logs)}
        </div>
    );
}
