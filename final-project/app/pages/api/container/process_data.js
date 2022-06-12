import { join, dirname } from "path";
import { Low, JSONFile } from "lowdb";
import { fileURLToPath } from "url";

const __dirname = dirname(fileURLToPath(import.meta.url));
const file = join(__dirname, "container.json");
const adapter = new JSONFile(file);
const db = new Low(adapter);

export default async function handler(req, res) {
    await db.read();

    const containers = db.data.container;

    var prev = {};
    var curr = {};
    var event_triggers = [];

    for (var con_key in containers) {
        const container = containers[con_key];
        const last30 = container.logs.slice(-30);
        const prev15 = last30.slice(0, 15);
        const curr15 = last30.slice(-15);

        prev["tem"] = prev15.reduce((a, b) => a + b.tem, 0) / 15;
        prev["hum"] = prev15.reduce((a, b) => a + b.hum, 0) / 15;
        prev["dpt"] = prev15.reduce((a, b) => a + b.dpt, 0) / 15;

        curr["tem"] = curr15.reduce((a, b) => a + b.tem, 0) / 15;
        curr["hum"] = curr15.reduce((a, b) => a + b.hum, 0) / 15;
        curr["dpt"] = curr15.reduce((a, b) => a + b.dpt, 0) / 15;

        // Tempertature event
        const temp_thresh = container.temp_thresh || 0;
        if (
            Math.sign(curr.tem - temp_thresh) !==
            Math.sign(prev.tem - temp_thresh)
        ) {
            // event_triggers.push("Temperature event triggered");
        }

        // Humidity event
        const hum_thresh = container.hum_thresh || 0;
        if (
            Math.sign(curr.hum - hum_thresh) !==
            Math.sign(prev.hum - hum_thresh)
        ) {
            // event_triggers.push("Humidity event triggered");
        }

        // Depth event
        const container_depth = container.con_depth;
        const amt_thresh = container.amt_thresh || 0;
        console.log(container_depth, amt_thresh);

        if (
            Math.sign((curr.dpt * 100) / container_depth - amt_thresh) !==
            Math.sign((prev.dpt * 100) / container_depth - amt_thresh)
        ) {
            event_triggers.push("Depth event triggered");
        }
    }

    res.status(200).json({
        previous15: prev,
        curr15: curr,

        events: event_triggers,
    });
}
