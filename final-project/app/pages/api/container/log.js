import { join, dirname } from "path";
import { Low, JSONFile } from "lowdb";
import { fileURLToPath } from "url";

const __dirname = dirname(fileURLToPath(import.meta.url));
const file = join(__dirname, "container.json");
const adapter = new JSONFile(file);
const db = new Low(adapter);

export default async function handler(req, res) {
    await db.read();
    db.data ||= { container: {} };

    const payload = req.body;
    const container_uuid = payload.uuid;
    const data = payload.data || null;

    var parsed = JSON.parse(data);

    var keyed = {
        tem: parsed["19b10001-e8f2-537e-4f6c-d104768a1214"],
        hum: parsed["19b10002-e8f2-537e-4f6c-d104768a1214"],
        dpt: parsed["19b10003-e8f2-537e-4f6c-d104768a1214"],
    };

    db.data.container[container_uuid].logs.push(keyed);

    res.status(200).json(db.data.container[container_uuid]);

    await db.write();
}
