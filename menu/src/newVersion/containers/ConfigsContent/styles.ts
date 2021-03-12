import { makeStyles } from "@material-ui/styles";
import { colors_ as colors } from "@utils";

export const useStyles = makeStyles({
  container: {
    display: "flex",
  },
  newConfig: {
    display: "flex",
    alignItems: "center",
    justifyContent: "space-between",
  },
  configListBtns: {
    display: "flex",
    alignItems: "center",
    justifyContent: "space-between",
  },
  configListBtns_left: {
    display: "flex",
    alignItems: "center",
  },
  configListBtns_save: {
    marginRight: 10,
  },
});
