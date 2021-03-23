const express = require("express");
const cors = require("cors");

const app = express();

const PORT = process.argv.find((s) => s.includes("port"))?.split("=")[1] || 2223;
const DIRECTORY = process.argv.find((s) => s.includes("dir"))?.split("=")[1] || "dist";
const DEV_PORT = 6060;

app.use(
  cors({
    origin: [`http://localhost:${PORT}`, `http://localhost:${DEV_PORT}`],
    optionsSuccessStatus: 200,
  })
);

app.use(express.static(DIRECTORY));

app.use(
  express.Router().get("/exit", (req, res) => {
    console.log(`[Node http server]: Stopped.`);
    res.json({ msg: 1 });
    process.exit(0);
  })
);

app.listen(PORT, () => {
  console.log(`[Node http server]: Started on port ${PORT}.`);
});
