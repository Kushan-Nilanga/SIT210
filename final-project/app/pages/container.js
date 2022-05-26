import axios from "axios";
import { useRouter } from "next/router";
import { useEffect, useState, useRef } from "react";

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
    tension: 0.3,
    elements: { point: { radius: 2 } },
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
            <h5>
                <a href="\"> &#60; Home </a>
            </h5>
            <h1>{container.name}</h1>
            <h6>uuid: {uuid}</h6>

            <div id="charts">
                <div style={{ width: "50%" }}>
                    <TemperatureGraph data={container.logs} />
                </div>
                <div style={{ width: "50%" }}>
                    <DepthGraph data={container.logs} />
                </div>
                <div style={{ width: "50%" }}>
                    <HumidityGraph data={container.logs} />
                </div>
            </div>
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
            arr.push({ x: element.time, y: 55 - element.dpt });
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
