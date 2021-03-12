import { makeStyles } from "@material-ui/styles";
import { colors } from "@utils";

export const useStyles = makeStyles({
  header: {
    padding: "10px 20px",

    display: "flex",
    justifyContent: "space-between",
    alignItems: "center",

    backgroundColor: colors.primary,
  },
  header_title: {
    fontWeight: 500,
    fontSize: 18,
    color: "#fff",
  },
  header_actions: {
    display: "flex",
    alignItems: "center",
  },
  header_action: {
    marginLeft: 7,
    width: 15,
    height: 15,

    borderRadius: 100,

    cursor: "pointer",

    "&-minimize": {
      backgroundColor: colors.green,
    },

    "&-options": {
      backgroundColor: colors.yellow,
    },

    "&-close": {
      backgroundColor: colors.red,
    },
  },
});
