import { makeStyles } from "@material-ui/styles";
import { colors } from "@utils";

export const useStyles = makeStyles({
  container: {
    width: 36,
    height: 36,

    display: "flex",
    alignItems: "center",
    justifyContent: "center",

    backgroundColor: colors.blue,
    borderRadius: 18,
  },
  icon: {
    display: "block",
    maxWidth: 20,
    maxHeight: 20,
  },
});
