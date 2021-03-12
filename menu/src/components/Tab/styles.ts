import { makeStyles } from "@material-ui/styles";
import { colors } from "@utils";

export type TProps = {
  active: boolean;
  enable: boolean;
};
export const useStyles = makeStyles({
  tab: {
    paddingTop: 4,
    paddingRight: 7,

    marginRight: 40,

    cursor: "pointer",
    position: "relative",
  },
  tab_title: {
    fontWeight: 500,
    fontSize: 18,
    color: (props: TProps) => (props.active ? colors.primary : colors.black),
    textTransform: "uppercase",
  },
  tab_badge: {
    width: 8,
    height: 8,

    backgroundColor: colors.green,
    borderRadius: 100,

    opacity: (props: TProps) => (props.enable ? 1 : 0),

    position: "absolute",
    right: 0,
    top: 0,
  },
});
