import { makeStyles } from "@material-ui/styles";
import { colors_ as colors, hexAlpha } from "@utils";

export const useStyles = makeStyles({
  container: {
    paddingLeft: 250,

    width: 985,
    height: 800,

    backgroundColor: colors.secondary,

    overflow: "hidden",
  },
  content: {
    padding: 50,
    height: "100%",
    width: "100%",

    overflowX: "hidden",
    overflowY: "auto",
  },
});
