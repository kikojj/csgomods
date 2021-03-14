import { makeStyles } from "@material-ui/styles";
import { colors, hexAlpha } from "@utils";

export const useStyles = makeStyles({
  container: {},
  label: {
    fontWeight: 400,
    fontSize: 14,
    color: "#fff",
  },
  helperText: {
    marginTop: 4,
    fontWeight: 400,
    fontSize: 12,
    color: "rgba(255,255,255,0.6)",
  },
  filters: {
    paddingLeft: 25,
  },
  filter: {
    marginTop: 5,
    padding: 5,

    display: "inline-block",

    background: "transparent",
    borderRadius: 2,

    fontSize: 14,
    color: "#fff",

    cursor: "pointer",

    transition: "0.2s background ease",

    "&:hover": {
      backgroundColor: hexAlpha(colors.primary, 5),
    },

    "&-active": {
      backgroundColor: hexAlpha(colors.primary, 10),
    },
  },
});
