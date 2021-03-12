import { makeStyles } from "@material-ui/styles";
import { colors } from "@utils";
import { TWindowSize } from "./index";

type TProps = {
  windowSize: TWindowSize;
};
export const useStyles = makeStyles({
  bg: {
    width: "100%",
    height: "100%",

    display: "flex",
    alignItems: "center",
    justifyContent: "center",

    backgroundColor: "#fff",
  },
  window: {
    width: (props: TProps) => (props.windowSize === "default" ? 1000 : "100%"),
    height: (props: TProps) => (props.windowSize === "default" ? "calc(100% - 40px)" : "100%"),

    display: "flex",
    flexDirection: "column",

    boxShadow: "0px 4px 4px rgba(0, 0, 0, 0.25)",
    borderRadius: (props: TProps) => (props.windowSize === "default" ? 4 : 0),

    overflow: "hidden",
  },
});
