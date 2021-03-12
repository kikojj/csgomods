import { makeStyles } from "@material-ui/styles";
import { colors, getColumnWidth } from "@utils";

const COLS = 2;
export const useStyles = makeStyles({
  global: {
    float: "left",
    width: getColumnWidth(COLS),
  },
  weapons: {
    float: "left",
    marginLeft: 100,
    width: getColumnWidth(COLS),
  },
});
