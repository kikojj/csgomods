import { makeStyles } from "@material-ui/styles";
import { colors, hexAlpha } from "@utils";

export const useStyles = makeStyles({
  preContainer: {
    paddingTop: 7,
    width: "100%",
  },
  container: {
    padding: "7px 10px",
    width: "100%",
    display: "flex",
    alignItems: "flex-end",

    backgroundColor: hexAlpha(colors.primary, 5),
    borderRadius: 2,

    position: "relative",
  },
  placeholder: {
    fontSize: 14,
    color: "#fff",

    position: "absolute",
    top: 7,
    left: 10,

    transform: "translate(0, 0px) scale(1)",
    transformOrigin: "top left",
    transition: "transform 200ms cubic-bezier(0, 0, 0.2, 1) 0ms",

    "&-focus": {
      transform: "translate(0, -14px) scale(0.8)",
      transformOrigin: "top left",
      transition: "transform 200ms cubic-bezier(0, 0, 0.2, 1) 0ms",
    },
  },
  input: {
    width: "100%",

    fontSize: 14,
    color: "#fff",

    backgroundColor: "transparent",
    border: 0,
    outline: "none",

    transition: "0.2s border ease",
  },
  helperText: {
    paddingLeft: 10,
    marginTop: 4,
    maxHeight: 0,

    fontSize: 12,
    color: "rgba(255,255,255,0.6)",

    overflow: "hidden",

    transition: "0.2s max-height ease-in-out",

    "&-show": {
      maxHeight: 14,
    },
  },
});
