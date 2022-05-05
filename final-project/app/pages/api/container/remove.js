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

    delete db.data.container[req.body.payload.id];

    res.status(200).json(db.data.container);
    await db.write();
}
