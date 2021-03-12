import { makeStyles } from "@material-ui/styles";
import { colors } from "@utils";

export type TProps = {
  active: boolean;
  enable: boolean;
};
export const useStyles = makeStyles({
  tabs: {
    padding: "26px 30px 29px 30px",
    display: "flex",
    alignItems: "center",
  },
});
