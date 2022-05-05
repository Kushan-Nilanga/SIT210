import { join, dirname } from "path";
import { Low, JSONFile } from "lowdb";
import { fileURLToPath } from "url";

const __dirname = dirname(fileURLToPath(import.meta.url));
const file = join(__dirname, "container.json");
const adapter = new JSONFile(file);
const db = new Low(adapter);

export default async function(req, res) {
    await db.read();

    db.data ||= { container: {} };

    if (req.query.uuid !== undefined)
        return res.status(200).json(db.data.container[req.query.uuid]);

    return res.status(200).json(db.data.container);
}
