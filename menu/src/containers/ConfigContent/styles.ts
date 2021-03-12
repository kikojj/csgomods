import { makeStyles } from "@material-ui/styles";
import { colors } from "@utils";

export const useStyles = makeStyles({
  configsList: {
    marginTop: 15,
    backgroundColor: "#fff",
  },
  configsList_item: {
    backgroundColor: "#fff",
  },
  configsList_actions: {
    marginTop: 14,
    display: "flex",
    justifyContent: "space-between",
    alignItems: "center",
  },
  configsList_actions_btnLoad: {
    marginLeft: 10,
  },
  newConfig: {
    display: "flex",
    alignItems: "center",
  },
  newConfig_input: {
    marginTop: 10,
    flex: 1,
  },
});
