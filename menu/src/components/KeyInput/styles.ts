import { makeStyles } from "@material-ui/styles";
import { colors, hexAlpha } from "@utils";

export const useStyles = makeStyles({
  container: {
    display: "flex",
    alignItems: "center",
    justifyContent: "space-between",
  },
  icon: {
    display: "block",

    "&:first-of-type": {
      marginRight: 5,
    },
  },
  icons: {
    marginRight: 7,
    display: "flex",
    alignItems: "center",
  },
  input: {
    padding: "7px 10px",
    width: "calc(100% - 41px)",

    flex: 1,
    backgroundColor: hexAlpha(colors.primary, 5),
    borderRadius: 2,

    fontSize: 14,
    color: "#fff",
  },
});
