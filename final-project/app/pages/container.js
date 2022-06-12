import axios from "axios";
import { useRouter } from "next/router";
import { useEffect, useState, useRef } from "react";
import Head from "next/head";

import { Card, Container } from "react-bootstrap";

/**
 * Chart imports
 */
import {
    Chart as ChartJS,
    TimeScale,
    LinearScale,
    PointElement,
    LineElement,
    Title,
    Tooltip,
    Legend,
} from "chart.js";
import { Line } from "react-chartjs-2";
import "chartjs-adapter-moment";

ChartJS.register(
    TimeScale,
    LinearScale,
    PointElement,
    LineElement,
    Title,
    Tooltip,
    Legend
);

const options = {
    response: true,
    tension: 0.4,
    elements: { point: { radius: 1 } },
    scales: {
        x: {
            type: "time",
            time: {
                unit: "hour",
            },
        },
    },
};

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
            <Head>
                <title>{container.name}</title>
            </Head>
            <h5>
                <a href="\"> &#60; Home </a>
            </h5>
            <h1>{container.name}</h1>

            <Card style={{ width: "100%" }}>
                <div style={{ margin: "1em" }}>
                    <h5>General Information</h5>
                    <b>UUID</b>: {uuid} <br />
                    <b>Container depth</b>: {container.con_depth} cm
                    {container.temp_thresh && (
                        <div>
                            <b>Temperature threshold:</b>{" "}
                            {container.temp_thresh} &#176;C
                            <br />
                        </div>
                    )}
                    {container.hum_thresh && (
                        <div>
                            <b>Humidity threshold:</b> {container.hum_thresh} %
                            <br />
                        </div>
                    )}
                    {container.amt_thresh && (
                        <div>
                            <b>Amount threshold:</b> {container.amt_thresh} %
                            <br />
                        </div>
                    )}
                </div>
            </Card>
            <br />
            <Card
                id="charts"
                style={{ width: "100%", padding: "1em", marginBottom: "1em" }}
            >
                <TemperatureGraph data={container.logs} />

                <DepthGraph data={container.logs} limit={container.con_depth} />

                <HumidityGraph data={container.logs} />
            </Card>
        </div>
    );
}

function TemperatureGraph(props) {
    const [metric, setMetric] = useState([]);

    useEffect(() => {
        if (props.data === undefined) return;

        var arr = [];
        props.data.forEach((element) => {
            arr.push({ x: element.time, y: element.tem });
        });
        setMetric(arr);
    }, [props.data]);

    return (
        <div id="temp-graph">
            <Line
                options={options}
                data={{
                    datasets: [
                        {
                            borderColor: "#36ab32",
                            data: metric,
                            label: "Temperature",
                        },
                    ],
                }}
            />
        </div>
    );
}

function DepthGraph(props) {
    const [data, setData] = useState([]);

    useEffect(() => {
        if (props.data === undefined) return;
        var arr = [];
        props.data.forEach((element) => {
            arr.push({ x: element.time, y: ((props.limit - element.dpt)*100+10)/props.limit });
        });
        setData(arr);
    }, [props.data]);

    return (
        <div id="dpt-graph">
            <Line
                options={options}
                data={{
                    datasets: [
                        { data: data, borderColor: "#ab3287", label: "Amount" },
                    ],
                }}
            />
        </div>
    );
}

function HumidityGraph(props) {
    const [data, setData] = useState([]);

    useEffect(() => {
        if (props.data === undefined) return;
        var arr = [];
        props.data.forEach((element) => {
            arr.push({ x: element.time, y: element.hum });
        });
        setData(arr);
    }, [props.data]);

    return (
        <div id="hum-graph">
            <Line
                options={options}
                data={{
                    datasets: [
                        {
                            data: data,
                            borderColor: "#db830f",
                            label: "Humidity",
                        },
                    ],
                }}
            />
        </div>
    );
}
