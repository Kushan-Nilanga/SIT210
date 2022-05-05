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

    const payload = req.body.payload;
    const container_uuid = payload.uuid;
    const data = payload.data || null;

    db.data.container[container_uuid].logs.push(data);

    res.status(200).json(db.data.container[container_uuid]);

    await db.write();
}
