import { makeStyles } from "@material-ui/styles";

export const useGlobalStyles = makeStyles({
  "@global": {
    "*, html, body": {
      margin: 0,
      padding: 0,
      boxSizing: "border-box",
      outline: "none",
      border: 0,
      fontFamily:
        "-apple-system, BlinkMacSystemFont, 'Roboto', Oxygen, Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue', sans-serif",
    },
  },
});
