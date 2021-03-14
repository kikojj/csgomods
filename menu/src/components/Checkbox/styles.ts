import { makeStyles } from "@material-ui/styles";
import { colors } from "@utils";

export type Props = {
  checked?: boolean;
};
export const useStyles = makeStyles({
  container: {
    width: 18,
    height: 18,

    border: (props: Props) => (props.checked ? "" : `2px solid ${colors.lightGray}`),
    boxSizing: "border-box",
    borderRadius: 9,

    backgroundColor: (props: Props) => (props.checked ? colors.primary : ""),

    cursor: "pointer",

    transition: "0.2s background, border ease",
  },
});
