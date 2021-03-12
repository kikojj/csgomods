import { makeStyles } from "@material-ui/styles";
import { colors } from "@utils";
import { RGBColor } from "react-color";

export type TProps = {
  marginTop?: number;
  color: RGBColor;
};
export const useStyles = makeStyles({
  colorPicker: {
    marginTop: (props: TProps) => props.marginTop,

    display: "flex",
    alignItems: "center",
  },
  colorPicker_label: {
    fontSize: 14,
    fontWeight: 400,
    color: colors.black,
  },
  colorPicker_value: {
    marginLeft: 10,
    width: 20,
    height: 20,

    border: "1px solid rgba(0,0,0,0.2)",
    borderRadius: 4,
    backgroundColor: (props: TProps) => `rgba(${props.color.r}, ${props.color.g}, ${props.color.b}, ${props.color.a})`,

    cursor: "pointer",
    position: "relative",
  },
  colorPicker_picker: {
    position: "absolute",
    top: 20,
    left: 20,
    zIndex: 1,
  },
});
