import { makeStyles } from "@material-ui/styles";
import { colors } from "@utils";
import { RGBColor } from "react-color";

export type TProps = {
  marginTop?: number;
};
export const useStyles = makeStyles({
  range: {
    marginTop: (props: TProps) => props.marginTop,
  },
  range_label: {
    fontSize: 14,
    fontWeight: 400,
    color: colors.black,
  },
});
