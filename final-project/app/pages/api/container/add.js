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
    const container_id = payload.id;

    db.data.container[container_id] = {
        name: payload.name,
        logs: [],
    };

    res.status(200).json(db.data.container[container_id]);
    await db.write();

    console.log("container add successful");
}
