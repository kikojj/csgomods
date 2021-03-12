import { makeStyles } from "@material-ui/styles";
import { colors } from "@utils";

export type TProps = {
  marginTop?: number;
};
export const useStyles = makeStyles({
  radio: {
    marginTop: (props: TProps) => props.marginTop,

    display: "flex",
    alignItems: "center",
  },
  radio_label: {
    fontSize: 14,
    fontWeight: 400,
    color: colors.black,
  },
});
