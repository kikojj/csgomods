const webpack = require("webpack");
const path = require("path");
const colors = require("colors");

//plugins
const HtmlWebpackPlugin = require("html-webpack-plugin");
const CopyPlugin = require("copy-webpack-plugin");
const { CleanWebpackPlugin } = require("clean-webpack-plugin");

//constants
const DEVELOPMENT = "development";
const PRODUCTION = "production";
const NODE_ENV = process.env.NODE_ENV || PRODUCTION;
const CLIENT_PORT = 6060;

/** @type {import('webpack').Configuration} */
module.exports = {
  mode: NODE_ENV,

  entry: "./src/index",
  output: {
    filename: `[name].js`,
    chunkFilename: `[name].bundle.js`,
    path: path.resolve(__dirname, "dist"),
    publicPath: "/",
  },

  resolve: {
    extensions: [".js", ".jsx", ".tsx", ".ts"],
    alias: {
      "@ts": path.resolve(__dirname, "src/ts"),
      "@utils": path.resolve(__dirname, "src/utils"),
      "@components": path.resolve(__dirname, "src/components"),
      "@containers": path.resolve(__dirname, "src/containers"),
      "@services": path.resolve(__dirname, "src/services"),
    },
  },

  devServer:
    NODE_ENV === DEVELOPMENT
      ? {
          port: CLIENT_PORT,
          hot: true,
          contentBase: ["./src", "./src/public"],
          watchContentBase: true,
          historyApiFallback: true,
          writeToDisk: true,
        }
      : {},

  optimization: {
    minimize: NODE_ENV === PRODUCTION,
    splitChunks: {
      chunks: "all",
      // name: false,
    },
    runtimeChunk: {
      name: (entrypoint) => `runtime-${entrypoint.name}`,
    },
  },

  plugins: [
    new CleanWebpackPlugin({
      cleanOnceBeforeBuildPatterns: "./dist/*",
      cleanAfterEveryBuildPatterns: ["./dist/*", "!*assets", "!*index.html"],
    }),
    new HtmlWebpackPlugin({
      template: "./src/public/index.html",
    }),
    new CopyPlugin({
      patterns: [
        {
          from: "./src/public/assets",
          to: "assets",
          noErrorOnMissing: true,
        },
      ],
    }),
  ],
  module: {
    rules: [
      {
        test: /\.(js|jsx)$/,
        use: useBabelLoader(),
        exclude: /node_modules/,
      },
      {
        test: /\.(ts|tsx)$/,
        use: [useBabelLoader(), "ts-loader"],
        exclude: /node_modules/,
      },
      {
        test: /\.css$/,
        use: ["style-loader", "css-loader"],
        exclude: /node_modules/,
      },
      {
        test: /\.(png|jpg|gif|svg|woff2|woff|eot|ico)$/,
        use: [`file-loader?name=assets/[name].[hash].[ext]`],
        exclude: /node_modules/,
      },
    ],
  },
};

function useBabelLoader() {
  return {
    loader: "babel-loader",
    options: {
      presets: ["@babel/preset-env", "@babel/preset-react"],
    },
  };
}
